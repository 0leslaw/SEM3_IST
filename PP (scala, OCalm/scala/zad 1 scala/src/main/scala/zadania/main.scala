package zadania

object main {
  def main(args: Array[String]): Unit = {
    val listsList: List[List[String]] = List[List[String]](List[String]("a", "b"), List[String]("c", "d"));

    println(zad1.flatten1(listsList))

    println(zad2.count("a" : String)(zad1.flatten1(listsList) : List[String]))

    println(zad3.replicate("a":String)(4 : Int))

    println(zad4.squareList(List[Int](1,2,3,4,5)))

    println(Zad5.isPalindrome(zad1.flatten1(listsList) : List[String]))
    println(Zad5.isPalindrome(List("a","b","b","a")))

    println(Zad6.listLenth(List("a","b","b","a")))

    println(zad7.solveInd(0.3)(256))
  }

}
