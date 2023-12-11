package zadania

object Laby3XD {
  def cutEnds[A](ListX : List[A]):List[A] = {
    removeLast(ListX.tail)
  }

  def removeLast[A](ListX: List[A]): List[A] = {
    if (ListX.tail.isEmpty)
      List[A]()
    else List[A](ListX.head) ::: removeLast(ListX.tail)
  }


  def groupElementsInto_valueCount_pairs[A](ListX : List[A]):List[(A,Int)] = {
    def helper(ListZ : List[A])(pair:(A,Int)):List[(A,Int)] =  {
      if (ListZ.isEmpty) {
        List[(A,Int)](pair)
      }else if (ListZ.head == pair._1){
        List[(A,Int)]():::helper(ListZ.tail)((pair._1,pair._2+1))
      }
      else
      List[(A,Int)](pair):::helper(ListZ.tail)((ListZ.head,1))
    }
    helper(ListX)((ListX.head,0))
  }



  //LABY 4 ZADANKO NA LEKCJI
  def sum(i1:Int,i2:Int):Int = {
    i1+i2
  }
  def accumulateClassic (list : List[Int])(entryState:Int)(f: (Int,Int)=>Int):Int = {
    def accumulateHelper(list: List[Int]): Int= list match {
      case Nil => 0
      case head :: tail => f(head,accumulateHelper(tail))
    }

    accumulateHelper(list)+entryState
  }

  def accumulateTail(list: List[Int])(entryState: Int)(f: (Int, Int) => Int): Int = {
    def accumulateTailHelper(list: List[Int])(subScore:Int): Int = list match {
      case Nil => subScore
      case head :: tail => accumulateTailHelper(tail)(f(subScore,head))
    }

    accumulateTailHelper(list)(entryState)
  }
  def sposobPrzeksztalcenia (f1:Double,f2:Double):(Double,Double) = {
    (f1+2,f2+1)
  }
  def przeksztalcenie(list : List[(Double,Double)])(f:(Double,Double)=>(Double,Double)): List[(Double,Double)]=list match {
    case Nil => List[(Double,Double)]()
    case head::tail => (f (head._1,head._2))::przeksztalcenie(tail)(f)
  }

  def lrepeat[A](k: Int)(lxs: LazyList[A]): LazyList[A] = {
    def loop (h: A)(i:Int):LazyList[A]  = {
      if(k<i){
        h #:: loop(h)(i+1)
      }else
        LazyList()
    }
    lxs match {
      case h #:: LazyList() => loop (h)(0)
      case (h:A) #:: (t:LazyList[A]) => loop (h)(0) #::: lrepeat(k)(t)
    }
  }

}
