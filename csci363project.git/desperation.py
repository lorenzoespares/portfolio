#!/usr/bin/python 
import urllib.request
import subprocess
import sys

def downloadPDF(fileURL):
    try:
        response = urllib.request.urlopen(fileURL)
        byteString = response.read()
        outputName = fileURL.split('/')[-1] #The pdf name would be the last value of list
        print("output file name (.pdf): ", outputName)
        f = open(outputName, 'wb')
        f.write(byteString)
        f.close()
        return outputName
    #Generic error, basically if at any time the program doesn't work, end the program
    except Exception:
        sys.exit(1) #Exit-Failure
        


# Converts pdf file to a text file, and then deletes the text file
def produceTextFile(outputName):
    #print("\nrunning pdftotext call")
    subprocess.call(" ".join(["pdftotext -enc ASCII7", outputName, "pdfTemp.txt"]), shell=True)
    print("removing temporary *.pdf")
    subprocess.call(" ".join(["rm -f", outputName]), shell=True)

def main(fileURL):
    outputName = downloadPDF(fileURL)
    produceTextFile(outputName)
    sys.exit() #Exit python

if __name__ == "__main__":
    #print(sys.argv[1])
    main(sys.argv[1])
