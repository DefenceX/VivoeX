/*
 * TinyFSM - Tiny Finite State Machine Processor
 *
 * Copyright (c) 2012-2018 Axel Burri
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

/* ---------------------------------------------------------------------
 * Version: 0.3.2
 *
 * API documentation: see "../doc/50-API.md"
 *
 * The official TinyFSM website is located at:
 * https://digint.ch/tinyfsm/
 *
 * Author:
 * Axel Burri <axel@tty0.ch>
 * ---------------------------------------------------------------------
 */

#ifndef HMICORE_TINYFSM_H_
#define HMICORE_TINYFSM_H_

#ifndef TINYFSM_NOSTDLIB
#include <type_traits>
#endif

// #include <iostream>
// #define DBG(str) do { std::cerr << str << std::endl; } while( false )
// DBG("*** dbg_example *** " << __PRETTY_FUNCTION__);

namespace gva::tinyfsm {

// --------------------------------------------------------------------------

struct Event {};

// ---------------------------------SRC_-----------------------------------------

#ifdef TINYFSM_NOSTDLIB
// remove dependency on standard library (silent fail!).
// useful in conjunction with -nostdlib option, e.g. if your compiler
// does not provide a standard library.
// NOTE: this silently disables all static_assert() calls below!
template <typename F, typename S>
struct is_same_fsm {
  static constexpr bool value = true;
};
#else
// check if both fsm and state class share same fsmtype
template <typename F, typename S>
struct is_same_fsm : std::is_same<typename F::fsmtype, typename S::fsmtype> {};
#endif

template <typename S>
struct _state_instance {
  using value_type = S;
  using type = _state_instance<S>;
  static S value;
};

template <typename S>
typename _state_instance<S>::value_type _state_instance<S>::value;

// --------------------------------------------------------------------------

template <typename F>
class Fsm {
 public:
  /// \brief Templated FSM
  using fsmtype = Fsm<F>;
  /// \brief Current state pointer
  using state_ptr_t = F *;
  /// \brief Current state pointer
  static state_ptr_t current_state_ptr;

  /// \brief public, leaving ability to access state instance (e.g. on Reset)
  template <typename S>
  static constexpr S &state(void) {
    static_assert(is_same_fsm<F, S>::value, "accessing state of different state machine");
    return _state_instance<S>::value;
  }

  ///
  /// \brief Check if in state
  ///
  /// \tparam S
  /// \return true
  /// \return false
  ///
  template <typename S>
  static constexpr bool is_in_state(void) {
    static_assert(is_same_fsm<F, S>::value, "accessing state of different state machine");
    return current_state_ptr == &_state_instance<S>::value;
  }

  /// state machine functions
 public:
  // explicitely specialized in FSM_INITIAL_STATE macro
  static void set_initial_state();

  /// \brief Reset state machine
  static void Reset() {}

  /// \brief Enter state
  static void enter() { current_state_ptr->entry(); }

  /// \brief start state
  static void start() {
    set_initial_state();
    enter();
  }

  ///
  /// \brief Dispatch a new state
  ///
  /// \tparam E
  /// \param event
  ///
  template <typename E>
  static void dispatch(E const &event) {
    current_state_ptr->react(event);
  }

  /// state transition functions
 protected:
  ///
  /// \brief Transition to new state
  ///
  /// \tparam S
  ///
  template <typename S>
  void transit(void) {
    static_assert(is_same_fsm<F, S>::value, "transit to different state machine");
    current_state_ptr->exit();
    current_state_ptr = &_state_instance<S>::value;
    current_state_ptr->entry();
  }

  ///
  /// \brief Transition to new state
  ///
  /// \tparam S
  /// \tparam ActionFunction
  /// \param action_function
  ///
  template <typename S, typename ActionFunction>
  void transit(ActionFunction action_function) {
    static_assert(is_same_fsm<F, S>::value, "transit to different state machine");
    current_state_ptr->exit();
    // NOTE: we get into deep trouble if the action_function sends a new event.
    // TODO(ross.newman@defencex.com.au): implement a mechanism to check for reentrancy
    action_function();
    current_state_ptr = &_state_instance<S>::value;
    current_state_ptr->entry();
  }

  ///
  /// \brief Transit to new state
  ///
  /// \tparam S
  /// \tparam ActionFunction
  /// \tparam ConditionFunction
  /// \param action_function
  /// \param condition_function
  ///
  template <typename S, typename ActionFunction, typename ConditionFunction>
  void transit(ActionFunction action_function, ConditionFunction condition_function) {
    if (condition_function()) {
      transit<S>(action_function);
    }
  }
};

template <typename F>
typename Fsm<F>::state_ptr_t Fsm<F>::current_state_ptr;

// --------------------------------------------------------------------------

template <typename... FF>
struct FsmList;

template <>
struct FsmList<> {
  /// \brief Set the inital state
  static void set_initial_state() {}
  /// \brief Enter state function
  static void enter() {}
  /// \brief Dispatch FSM
  template <typename E>
  static void dispatch(E const &) {}
};

template <typename F, typename... FF>
struct FsmList<F, FF...> {
  using fsmtype = Fsm<F>;

  ///
  /// \brief Set the initial state object
  ///
  ///
  static void set_initial_state() {
    fsmtype::set_initial_state();
    FsmList<FF...>::set_initial_state();
  }

  ///
  /// \brief Reset
  ///
  ///
  static void Reset() {
    F::Reset();
    FsmList<FF...>::Reset();
  }

  ///
  /// \brief Enter
  ///
  ///
  static void enter() {
    fsmtype::enter();
    FsmList<FF...>::enter();
  }

  ///
  /// \brief Start
  ///
  ///
  static void start() {
    set_initial_state();
    enter();
  }

  ///
  /// \brief Dispatch
  ///
  /// \tparam E
  /// \param event
  ///
  template <typename E>
  static void dispatch(E const &event) {
    fsmtype::template dispatch<E>(event);
    FsmList<FF...>::template dispatch<E>(event);
  }
};

// --------------------------------------------------------------------------

template <typename... SS>
struct StateList;
template <>
struct StateList<> {
  /// \brief Reset state list
  static void Reset() {}
};
template <typename S, typename... SS>
struct StateList<S, SS...> {
  /// \brief Reset state
  static void Reset() {
    _state_instance<S>::value = S();
    StateList<SS...>::Reset();
  }
};

// --------------------------------------------------------------------------

template <typename F>
struct MooreMachine : tinyfsm::Fsm<F> {
  /// \brief entry actions in some states
  virtual void entry(void) {}
  /// \brief no exit actions
  void exit(void) {}
};

template <typename F>
struct MealyMachine : tinyfsm::Fsm<F> {
  // input actions are modeled in react():
  // - conditional dependent of event type or payload
  // - transit<>(ActionFunction)VIEW_GVA_H
  /// \brief no entry actions
  void entry(void) {}
  /// \brief no exit actions
  void exit(void) {}
};

}  // namespace gva::tinyfsm

#define FSM_INITIAL_STATE(_FSM, _STATE)                  \
  namespace tinyfsm {                                    \
  template <>                                            \
  void Fsm<_FSM>::set_initial_state(void) {              \
    current_state_ptr = &_state_instance<_STATE>::value; \
  }                                                      \
  }

#endif  // HMICORE_TINYFSM_H_
