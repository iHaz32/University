(define (domain projectDomain) ; Domain name must match problem’s
  ; Define what the planner must support to execute this domain
  (:requirements
    :strips ; basic preconditions and effects
    :negative-preconditions ; to use not in preconditions
    :equality ; to use = in preconditions
    :disjunctive-preconditions
   ) 
  (:predicates
    (dock ?x)
    (container ?x)
    (robot ?x)
    (isConnected ?d1 ?d2)
    (isGrabbed ?c)
    (isOnTop ?c)
    (isOnStack ?c)
    (isBusy ?r)
    (on ?c1 ?c2)
    (containerOnDock ?c ?d)
    (robotOnDock ?r ?d)
  )  
  (:action grabSingle
    :parameters (?r ?c ?d)
    :precondition
      (and (robot ?r) (container ?c) (dock ?d) (not (isGrabbed ?c)) (isOnTop ?c) (not (isBusy ?r)) (not (isOnStack ?c)) (containerOnDock ?c ?d) (robotOnDock ?r ?d))
    :effect
      (and (isGrabbed ?c) (isBusy ?r)
      (not (isOnTop ?c)) (not (containerOnDock ?c ?d))
      )
  )
  (:action grabFromStack
    :parameters (?r ?c ?cUnder ?d)
    :precondition
      (and (robot ?r) (container ?c) (container ?cUnder) (dock ?d) (not (isGrabbed ?c)) (isOnTop ?c) (isOnStack ?c) (not (isBusy ?r)) (on ?c ?cUnder) (containerOnDock ?c ?d) (robotOnDock ?r ?d))
    :effect
      (and (isGrabbed ?c) (isBusy ?r) (isOnTop ?cUnder)
      (not (isOnTop ?c)) (not (on ?c ?cUnder))  (not (containerOnDock ?c ?d)) (not (isOnStack ?c))
      )
  )  
  (:action throwSingle
    :parameters (?r ?c ?d)
    :precondition
      (and (robot ?r) (container ?c) (dock ?d) (isGrabbed ?c) (isBusy ?r) (robotOnDock ?r ?d))
    :effect
      (and (isOnTop ?c) (containerOnDock ?c ?d)
      (not (isBusy ?r)) (not (isGrabbed ?c))
      )
  )
  (:action throwToStack
    :parameters (?r ?c ?cUnder ?d)
    :precondition
      (and (robot ?r) (container ?c) (dock ?d) (container ?cUnder) (isGrabbed ?c) (isBusy ?r) (isOnTop ?cUnder) (robotOnDock ?r ?d) (containerOnDock ?cUnder ?d))
    :effect
      (and (isOnTop ?c) (containerOnDock ?c ?d) (on ?c ?cUnder) (isOnStack ?c)
      (not (isBusy ?r)) (not (isGrabbed ?c)) (not (isOnTop ?cUnder))
      )
  )
  (:action robotMove
    :parameters (?r ?d1 ?d2)
    :precondition
      (and (robot ?r) (dock ?d1) (dock ?d2) (robotOnDock ?r ?d1) (isConnected ?d1 ?d2))
    :effect
      (and (robotOnDock ?r ?d2)
      (not (robotOnDock ?r ?d1))
      )
  )
)