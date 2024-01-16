package Firma;

import java.security.InvalidParameterException;

public abstract class APracownik {
    protected String imie;
    protected String nazwisko;
    protected String pesel;
    protected int placa;

    public APracownik(String imie, String nazwisko, String pesel, int placa) {
        this.imie = imie;
        this.nazwisko = nazwisko;
        this.pesel = pesel;
        this.placa = placa;
    }

    public void dajPodwProc(int ileProcent){
        if (ileProcent < 0){
            throw new InvalidParameterException();
        }

        placa += placa*ileProcent/100;
    }

    public String getImie() {
        return imie;
    }

    public void setImie(String imie) {
        this.imie = imie;
    }

    public String getNazwisko() {
        return nazwisko;
    }

    public void setNazwisko(String nazwisko) {
        this.nazwisko = nazwisko;
    }

    public String getPesel() {
        return pesel;
    }

    public void setPesel(String pesel) {
        this.pesel = pesel;
    }

    public int getPlaca() {
        return placa;
    }

    public void setPlaca(int placa) {
        this.placa = placa;
    }

    @Override
    public String toString() {
        return
                "imie='" + imie + '\'' +
                ", nazwisko='" + nazwisko + '\'' +
                ", pesel='" + pesel + '\'' +
                ", placa=" + placa +
                '}';
    }

}
