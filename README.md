# Client-server project on C99 for macOS

Project created as a course work for MTUCI in December 2021.
The task was to implement different technologies for communications between two or more processes.

## Brief overview

This project consists of:
<li> 1 Client </li>
<li> 2 Servers </li>
<li> 2 Log servers </li>
<br>
<p>
  Each server can accept multiple clients connections via sockets. Every client can connect 1 server, send certain commands and disconect.
  Each server connected to its own log server (if started) that get log strings using fifo (named pipes).
</p>
<br>
<p>
  Most interesting technologies implemented in the project:
  <li> multi-proccessing </li>
  <li> signals and signals handlers </li>
  <li> named pipes </li>
  <li> sockets </li>
  <li> sysctl lib </li>
</pi>
