# runway-reservation-scheduler

### Source: MIT Lecture 5, Unit 2 : Sorting and trees 
[Video Resource](https://www.youtube.com/watch?v=9Jry5-82I68) ,
[Lecture Notes](https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-006-introduction-to-algorithms-fall-2011/lecture-notes/)

Runway reservation scheduling is a scheduling problem which needs a data structure for fast insertion and deletion, thus
 BSTs are best for this type of problem.

**Problem Statement:**

Design a data structure for a **Real life Scenario** of a runway reservation system.
which should be able to handle :

* Each request will come with a time of landing, on which the plane is suppose to be land.
* Make sure each landing are `k` Minutes away from each other. Call this `K minutes check`.
    * for example 
        * If k=3, and there is a landing scheduled in next 5 mins, then there should not be a landing in next 4 mins or 6 mmins (as the k min check will fail).
* For a given time `t`, show all the landing scheduled for `t` and after it.
* Each time you delete a node or insert a node, the no. of landings must be managed in recursive calls.

### For detailed explanation, watch the [video](https://www.youtube.com/watch?v=9Jry5-82I68).
