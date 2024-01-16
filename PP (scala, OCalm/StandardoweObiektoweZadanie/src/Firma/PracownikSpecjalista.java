package Firma;

import java.util.function.Function;

public class PracownikSpecjalista extends APracownik{
    private Function<Integer,Integer> premia;

    public PracownikSpecjalista(String imie, String nazwisko, String pesel, int placa, Function<Integer, Integer> premia) {
        super(imie, nazwisko, pesel, placa);
        this.premia = premia;
    }

    public void zwiekszPlaceOPremie(int parametrDoUstaleniaPremii){
        placa += premia.apply(parametrDoUstaleniaPremii);
    }

    public Function<Integer, Integer> getPremia() {
        return premia;
    }

    public void setPremia(Function<Integer, Integer> premia) {
        this.premia = premia;
    }

    @Override
    public String toString() {
        return "PracownikSpecjalista{" +

                super.toString();
    }
}
