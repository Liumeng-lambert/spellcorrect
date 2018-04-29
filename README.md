# spellcorrect
  important ：Draw on the experience of Muduo in Network programming.
# UML:
  
  
# basic function：
  build dictionary and index from corpus you provide，and though network，client send a query to server，server will search it in cache（if cached），else will search in index，and send back the query-result.
# network
  socket + tcp + epoll(LT in 1st ed.)
# index
  reverse index and build from two english file(will support Chinese later)
# cache
  
# timer-thread
  
# spellcorrect
