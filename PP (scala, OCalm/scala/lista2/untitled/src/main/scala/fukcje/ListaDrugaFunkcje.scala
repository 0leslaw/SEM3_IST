package fukcje

object ListaDrugaFunkcje {
  def fib (n : Int):Int =
    n match {
      case 0 => 0
      case 1 => 1
      case _ => fib(n-1) + fib(n-2)
  }

  def fibTail(num: Int): BigInt = {
    @scala.annotation.tailrec
    def fibTailHelper(n: Int, prev: Int, current: Int): Int = n match {
      case 0 => prev
      case 1 => current
      case _ => fibTailHelper(n - 1, prev, prev + current)
    }

    fibTailHelper(num, 0, 1)
  }
  def root3(number :Double):Double = {
    def loop (i : Int)(prev : Double):Double = {
      if (Math.abs(Math.pow(prev,3)- number) >= (Math.pow(10,(-15)) * number))
      loop (i+1) (prev + (((number/(prev*prev))-prev)/3.0))
      else prev
    }
    if (number<=1)
    loop(0)(number)
    else
      loop(0)(number/3)
  }

  def isSegment[A](listPair : (List[A],List[A])) : Boolean = listPair match{
    case (h1::t1,h2::t2) if h1 == h2 => isSegment((t1,t2):(List[A],List[A]))
    case (h1::t1,h2::t2) if h1 != h2 => false
    case (h1::t1,Nil) => false
    case _ => true
  }

  def changeNth[A](pairListPairIndexElement : (List[A], (Int, A) ) ): List[A] = {
    def loop (i:Int, list: List[A]): List[A] = pairListPairIndexElement match {
    case (Nil, (n, elem) ) => Nil
    case (h::t, (n, elem) ) if n==i => List[A](elem):::loop(i+1, )
    case (h::t, (n, elem) ) if n!=i => List[A](h):::loop(i+1, )
    }
    loop(0)()
  }
}
