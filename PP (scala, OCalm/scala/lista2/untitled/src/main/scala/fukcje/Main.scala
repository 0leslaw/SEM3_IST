package fukcje

object Main {
  def main(args: Array[String]): Unit = {
    println(ListaDrugaFunkcje.root3(8))
    println(ListaDrugaFunkcje.root3(0.125))

    var l : List[Int] = List[Int](1,2,0,2,2)
    var List(_,_,x:Int,_,_) = l
    var List((_,_),(y,_)) = List[Int]((3,2),(0,3))



  }
}
