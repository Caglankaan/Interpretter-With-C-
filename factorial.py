x = 5

p=[]
for i in range(0,x+1):
    if(len(p) == 0):
        p.append(0)
    else:
        p.append(p[i-1]+1/x)

for i in range(0, len(p)):
    print("p",i," is: ", p[i])