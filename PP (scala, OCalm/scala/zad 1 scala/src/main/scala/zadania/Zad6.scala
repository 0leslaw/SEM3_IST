package zadania

object Zad6 {
  def listLenth[A](ListX : List[A]) : Int = {
    if(ListX.isEmpty)
      0
    else 1 + listLenth(ListX.tail)
  }
}
