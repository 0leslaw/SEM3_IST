package zadania

object zad3 {
    def replicate[A](toBeReplicated : A)(howManyTimes : Int) : List[A] = {
        if(howManyTimes == 0){
            List[A]()
        }else
            List[A](toBeReplicated) ::: replicate(toBeReplicated,howManyTimes-1)
    }

}
