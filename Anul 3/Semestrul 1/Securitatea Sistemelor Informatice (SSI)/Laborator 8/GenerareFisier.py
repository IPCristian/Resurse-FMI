file = open('generatedFile.txt','w')

for i in range(10000000):
    file.write('parola'+str(i)+'\n')

file.close()