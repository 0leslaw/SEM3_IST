package Firma;

public class Zadanie {
    private String nazwa;
    private StatusZadania status;
    private TrybZadania tryb;
    private APracownik wykonawcaZadania;

    public Zadanie(String nazwa, StatusZadania status, TrybZadania tryb, APracownik wykonawcaZadania) {
        this.nazwa = nazwa;
        this.status = status;
        this.tryb = tryb;
        this.wykonawcaZadania = wykonawcaZadania;
    }

    public enum StatusZadania{
        W_PRZYGOTOWANIU,
        W_TOKU,
        ZAKONCZONE
    }
    public enum TrybZadania{
        NORMALNY,
        PILNY
    }

    public String getNazwa() {
        return nazwa;
    }

    public void setNazwa(String nazwa) {
        this.nazwa = nazwa;
    }

    public StatusZadania getStatus() {
        return status;
    }

    public void setStatus(StatusZadania status) {
        this.status = status;
    }

    public TrybZadania getTryb() {
        return tryb;
    }

    public void setTryb(TrybZadania tryb) {
        this.tryb = tryb;
    }

    public APracownik getWykonawcaZadania() {
        return wykonawcaZadania;
    }

    public void setWykonawcaZadania(APracownik wykonawcaZadania) {
        this.wykonawcaZadania = wykonawcaZadania;
    }
    public Boolean czyZadanieSpelniaParametry(String nazwa, StatusZadania statusZadania, APracownik wykonawcaZadania){
        if (nazwa != null && !this.nazwa.equals(nazwa))
            return false;
        if (statusZadania != null && !this.status.equals(statusZadania))
            return false;
        if (wykonawcaZadania != null && !this.wykonawcaZadania.equals(wykonawcaZadania))
            return false;

        return true;
    }

    @Override
    public String toString() {
        return "Zadanie{" +
                "nazwa='" + nazwa + '\'' +
                ", status=" + status +
                ", tryb=" + tryb +
                ", wykonawcaZadania=" + wykonawcaZadania +
                '}';
    }
}
