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
}
