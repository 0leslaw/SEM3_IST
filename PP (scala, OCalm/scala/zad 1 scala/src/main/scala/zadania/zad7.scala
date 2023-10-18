package zadania

object zad7 {
  def solveInd(c : Int)(n : Int) : Int = {
    if(n == 1){
      1
    }else solveInd(c,(n/2)) + 2*(scala.math.log(n))
  }
}
