package zadania

object zad2 {
  def count[A](toBeCounted : A)(ListX : List[A]): Int = {
    if (ListX.isEmpty) {
      0
    } else if (ListX.head == toBeCounted){
      1 + count(toBeCounted, ListX.tail)
    }else
      count(toBeCounted, ListX.tail)
  }


}
