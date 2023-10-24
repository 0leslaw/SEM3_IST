package zadania

object zad7 {
  def solveInd(c : Double)(n : Double) : Double = {
    if(n == 1){
      1
    }else solveInd(c)(n/2) + 2*(scala.math.log10(n))
  }
}
