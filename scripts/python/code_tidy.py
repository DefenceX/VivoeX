from pathlib import Path
  
# Using '*' pattern 
types = ('*.cc','*.h') # the tuple of file types

files_grabbed = []
for files in types:
    files_grabbed.extend(Path('.').rglob(files))

updated_header = ""
for file in files_grabbed:
    print("Processing", file)
    f = open(file, "r")
    for num, line in enumerate(f, 1):
        if "\\brief" in line:
            print('found at line:', num)
            f.seek(0)
            updated_header = ""
            for i in range(num-1):
                updated_header=  updated_header + next(f)
            updated_header = updated_header.replace('///', '//')
            counter = 0
            f.seek(0)
            for l in f:
                # print(counter, l)
                if (counter >= num-1):
                    updated_header = updated_header + l
                counter+=1
            print(updated_header)
            # Time to write file back out
            f.close()     
            f = open(file, "w")
            f.write(updated_header)
            f.close()    
            break



