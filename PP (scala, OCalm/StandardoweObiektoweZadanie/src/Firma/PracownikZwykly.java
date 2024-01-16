package Firma;

public class PracownikZwykly extends APracownik{
    public PracownikZwykly(String imie, String nazwisko, String pesel, int placa) {
        super(imie, nazwisko, pesel, placa);
    }

    @Override
    public String toString() {
        return "PracownikZwykly{"+ super.toString();
    }
}
