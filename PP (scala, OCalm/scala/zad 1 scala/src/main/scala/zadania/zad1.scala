package zadania

object zad1 {
  def flatten1[A](ListX : List[List[A]]) : List[A] = {
    if (ListX.isEmpty){
      List[A]();
    }else{
      ListX.head:::flatten1(ListX.tail);
    }

  }
}
