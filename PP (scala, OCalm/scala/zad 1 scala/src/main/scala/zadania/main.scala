package zadania

object main {
  def main(args: Array[String]): Unit = {
//    val listsList: List[List[String]] = List[List[String]](List[String]("a", "b"), List[String]("c", "d"));
//
//    println(zad1.flatten1(listsList))
//
//    println(zad2.count("a" : String)(zad1.flatten1(listsList) : List[String]))
//
//    println(zad3.replicate("a":String)(4 : Int))
//
//    println(zad4.squareList(List[Int](1,2,3,4,5)))
//
//    println(Zad5.isPalindrome(zad1.flatten1(listsList) : List[String]))
//    println(Zad5.isPalindrome(List("a","b","b","a")))
//
//    println(Zad6.listLenth(List("a","b","b","a")))
//
//    println(zad7.solveInd(0.3)(256))
//
//
//
//    println(Laby3XD.cutEnds(List("a","b","b","a","a","b","b","a")))
//    println(Laby3XD.groupElementsInto_valueCount_pairs(List("a","b","b","a","a","b","b","a")))
//
//    println(Laby3XD.accumulateClassic(List[Int](1,2,3,4,5))(0)(Laby3XD.sum))
//    val listaPar: List[(Double, Double)] = List(
//      (1.0, 2.0),
//      (3.5, 4.7),
//      (0.8, 2.3),
//      (5.5, 1.2)
//    )
//    println(Laby3XD.przeksztalcenie(listaPar)(Laby3XD.sposobPrzeksztalcenia))

    println(Laby3XD.lrepeat(3)(LazyList.fill(2)(2)).toList)

  }

}
