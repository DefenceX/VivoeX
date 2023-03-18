
# Creation of alarms
To generate sounds install ***apt install tones***

## Threat
```
tones -f -w threat.wav -loop square 100 1000 0 1000 0 1000 0 1000 0 1000 0 1000 0 1000 0 1000 0 1000 0 1000 0 1000 0 1000 0 1000 0 1000 0 1000 0 1000 0 1000 0 1000 & aplay threat.wav
```
## Caution
```
tones -f -w caution.wav -loop square 200 800 0 700 0 800 0 700 0 800 0 700 0 800 0 700 0 800  & aplay caution.wav
```
## Warning
```
tones -f -w warning.wav -loop square 200 400 0 400 0 400 0  & aplay warning.wav
```
## Testing
Pipe the file to aplay to hear it
```
tones -f -w test.wav -loop square 200 800 0 700 0 & aplay test.wav
```

