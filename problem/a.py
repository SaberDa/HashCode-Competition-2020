to_read = "a_example.txt"

global_books = []
libraries = []

class book:
    def __init__(self,id,score):
        self.id,self.score=id,score

class library:
    def __init__(self,signup,booksperday):
        self.signup,self.booksperday = signup,booksperday
        self.books = []

f = open(to_read,"r")
lines = f.readlines()

for id,score in enumerate(lines[1].split()):
    global_books.append(book(id,score))

n = 2
while n < len(lines):
    this_library = lines[n:n+2]
    parms = this_library[0].split()
    libraries.append(library(int(parms[1]),int(parms[2])))
    for i in this_library[1].split():
        libraries[-1].books.append(global_books[int(i)])
    n += 2