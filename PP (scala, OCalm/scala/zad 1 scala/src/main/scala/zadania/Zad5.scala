package zadania

object Zad5 {
  def isPalindrome[A](ListX : List[A]) : Boolean = {
    if(ListX.isEmpty){
      true
    }else
    if (ListX.head == ListX.last)
      isPalindrome(removeLast(ListX.tail))
    else
      false

  }
  def removeLast[A](ListX : List[A]) : List[A] = {
    if (ListX.tail.isEmpty)
      List[A]()
    else List[A](ListX.head):::removeLast(ListX.tail)
  }
}
