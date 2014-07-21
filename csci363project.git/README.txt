Team Members:
Thomas Ludwig
Lorenzo Espares
Philipp Leite


PHASE 1
------------------------------------------------------------------------------------------
How to use program:
./url-extractor <compane> <path> [appnum]

Example:
./url-extractor eg.bucknell.edu /~cs363/2014-spring/

Essentially, our approach to solve this problem was to split the project 
into separate components. The three major components of this project are extracting
the html code from a web page into chunks, using a linked list to store those chunks 
into memory, and then parsing those chunks to build a list of urls. 

One of the major highlights of this project is how well we were able to extract the html
code from a website, and store that html code into a linked list structure. The extraction
process is very scalable, as we were able to generate a linked list of the html code for 
very large websites. 

There were several major difficulties we encountered during this project. One of the
biggest problems we found was parsing the urls from the html code. String manipulation 
in C is difficult to begin with, but dealing with a linked list of html code chunks where
a link tag could be in one node, and the link itself could be in a different node really
compounded the problem. To solve this we made several helper functions to deal with the 
the task of going from html chunks to a list of absolute urls. In addition, we utilized 
the findStrLoc and findloc functions in file stringutils.c to determine if a <a href> tag
was in the current node. 

Another major difficulty in this project was how to make use of functions in the source 
files such as url.c, tcplib.c, stringutils.c, as there was little documentation regarding 
how the functions worked, how the input parameters of the function worked, etc. For example,
it took us quite a while to realize we have to omit the "http://" when we input a url. 






PHASE 2
------------------------------------------------------------------------------------------
How to use program:
./extraction <compane> <path> [appnum]
./searchserver
In web client:
    + enter in url:--  http://machinename:14016    (hardcoded port number)
    + enter search query in text box

Example:
./extraction eg.bucknell.edu /~cs363/2014-spring/
./searchserver
In web client:
    + http://brki164-lnx-5:14016
    + enter query "client"
    + query is found, returns URLs where search term exists.

For this second phase, our approach was initially to implement a hash table that would
be used to store the list of words parsed using the extraction program, and then take in
a query from a web client which would be handled by the searchserver program. We attempted
to keep close to the guidelines that were set in the beginning of this phase and followed
the hints closely, which eventually led us to a working search engine. The extraction 
program handled parsing the words of the web page, which are written to the file named
searchwords.txt. A hash table is built in the server which is used to handle queries from
the web client. The implementation for the hash table we make use of comes from search.h, 
which is part of GNU's C library.

A major highlight for this phase was Tom's work in implementing a String structure which 
has similar behavior to how python treats strings. As a result, certain parts of this
second phase such as retrieving the search query for the web client's POST and building 
a complete list of words from the web page were able to be done very easily thanks to 
Tom's implementation. Similarly, the hash table implemented for the search server works
hand in hand with this new String implementation.

Difficulties that the group faced lie mostly in retrieving the query from the web client.
Using normal string manipulation provided by C made this very difficult. As stated 
earlier, the new String manipulation helped us overcome this difficulty very quickly.
There was also the problem in working separately since multiple pushes to the git 
repository resulted in multiple Makefiles which resulted in a bit of confusion.

A major difficulty that we faced and are currently facing is the copious amounts of files.
As we continue to the next phase of the project, there are only going to be more files
in the directory which can cause a lot of confusion when creating new classes in order
to tackle future phases of the project.






PHASE 3
------------------------------------------------------------------------------------------
How to use program:
./crawler <compane> <path>
./searchserver
In web client:
    + enter in url:--  http://machinename:14016    (hardcoded port number)
    + enter search query in text box

Example:
./crawler eg.bucknell.edu /~cs363/2014-spring/
./searchserver
In web client:
    + http://brki164-lnx-5:14016
    + enter query "client"
    + query is found, returns URLs where search term exists.

For this third phase, we knew that the previously implemented hash table would be unable 
to handle such a large amount of words taken from the websites that the crawler passes
through, which could range from 1 to 1000 depending on the setting of CRAWL_COUNT. Since
this was the case, Tom decided to implement a GDB gnu database, which would store keys
and values as the indexing system proposed in the project website. The keys would be the
words and the values would be a list of items that contained the URLS and document 
frequency, as stated on the graphic of building an indexing system.

The database was a major highlight for this phase since it was scalable and had the ability
to hold a large amount of data with a similarly efficient fetching time. The database did
come with its own difficulties, mostly due to memory and storage that was used in order
to store this data that would often result in segmentation faults in the initial stages 
of our project. The database often grew to over 500MB for only crawling through 10 or so 
pages, which was not ideal in terms of memory management for our project. It was also a new 
tool to work with so we needed time to become familiarized with how to set and retrieve
keys and values from the database.

Difficulties that the group faced included dealing with .pdf and.xml paths. Since our
original extractor worked only with .html files, it was difficult to reimplement it to
be able to deal with .pdf and .xml files. Our lack of C experience didnt help to make
the problem any easier and caused many wasted hours when we tried to dealt with the pdf
problem. Similarly, there was no communication between team members which resulted in a
lack of meetings to work on the project and a disproportional amount of work for one of our 
team members, which was not fair to him in any way whatsoever. 

We addressed the difficulty of file management in this phase, sorting files into folders
that they properly belonged in. This made our testing a little easier and made it so that
we could debug our program at a slightly more efficient rate.
