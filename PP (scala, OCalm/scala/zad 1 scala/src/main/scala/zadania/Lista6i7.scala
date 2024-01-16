package zadania

object Lista6i7 {
  def whileLoop(warunek : => Boolean)(blok: => Unit): Unit= {
    if (!warunek(zmienna))
      whileLoop(f (zmienna))(warunek)(f)
    else
      zmienna
  }
}
