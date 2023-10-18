package zadania

object zad4 {
  def squareList(ListX : List[Int]):List[Int] = {
    if(ListX.isEmpty){
      List[Int]()
    }else {
      List[Int](ListX.head*ListX.head):::squareList(ListX.tail)
    }
  }
}
