# Producer-Consumer


In this project, we will study to apply multithreaded programming to implement a producer-consumer solution that prints a sequence of consecutive integers starting from 0, using a fixed size buffer (i.e, bounded buffer). As we mentioned in the class, multithreaded programming can be supported in the user level, more specifically, libraries in the user level. The library we will use for this project is called pthread.
In this project, a producer repeatedly generates the next consecutive integer and insert it into the slot indicated by the flag in; a consumer repeatedly pick up an item from the slot indicated by the flag out.
