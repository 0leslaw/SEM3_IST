package Firma;

import java.security.InvalidParameterException;
import java.util.ArrayList;
import java.util.Collections;

public class ListaZasobow {
    private ArrayList<APracownik> listaPracownikow;
    private ArrayList<Zadanie> listaZadan;

    public ListaZasobow() {
        listaPracownikow = new ArrayList<>();
        listaZadan = new ArrayList<>();
    }
    public ListaZasobow(ArrayList<APracownik> listaPracownikow, ArrayList<Zadanie> listaZadan) {
        this.listaPracownikow = listaPracownikow;
        this.listaZadan = listaZadan;
    }
    public void dodajPracownika(APracownik pracownik){
        listaPracownikow.add(pracownik);
    }
    public void dodajZadanie(Zadanie zadanie){
        listaZadan.add(zadanie);
    }
    public APracownik znajdzPoPeselu(String PESEL){
        for (APracownik pracownik : listaPracownikow)
            if (pracownik.getPesel().equals(PESEL))
                return pracownik;
        throw new InvalidParameterException();
    }
    public void zwiekszWszystkimOProcent(int ileProcent){
        for (APracownik pracownik : listaPracownikow)
            pracownik.dajPodwProc(ileProcent);
    }
    public void przydzielPremie(PracownikSpecjalista pracownikSpecjalista, int parametrDoUstaleniaPremii){
        pracownikSpecjalista.zwiekszPlaceOPremie(parametrDoUstaleniaPremii);
    }
    //W TEJ FUNKCJI PODANIE NULLA OZNACZA ZE NIE FILTRUJEMY PO NULLOWANYM PARAMETRZE
    public ArrayList<Zadanie> filtrujListeZadanIPosortujPilnoscia(String nazwa, Zadanie.StatusZadania statusZadania, APracownik wykonawca){
        ArrayList<Zadanie> odfiltrowana = new ArrayList<>();
        for (Zadanie zadanie : listaZadan)
            if (zadanie.czyZadanieSpelniaParametry(nazwa, statusZadania, wykonawca))
                odfiltrowana.add(zadanie);

        return sortujPilnoscia(odfiltrowana);
    }
    public ArrayList<Zadanie> sortujPilnoscia(ArrayList<Zadanie> doSortowania){
        int i = 0;
        int j = doSortowania.size()-1;
        while (i != j){
            while (i != j && doSortowania.get(i).getTryb() != Zadanie.TrybZadania.NORMALNY)
                i++;
            while (i != j && doSortowania.get(j).getTryb() != Zadanie.TrybZadania.PILNY)
                j--;
            Collections.swap(doSortowania,i,j);
        }
        return doSortowania;
    }

    @Override
    public String toString() {
        return "ListaZasobow{\n\n" +
                "listaPracownikow=" + listaPracownikow +
                "\n\n, listaZadan=" + listaZadan +
                "\n}\n\n";
    }

    public ArrayList<APracownik> getListaPracownikow() {
        return listaPracownikow;
    }

    public void setListaPracownikow(ArrayList<APracownik> listaPracownikow) {
        this.listaPracownikow = listaPracownikow;
    }

    public ArrayList<Zadanie> getListaZadan() {
        return listaZadan;
    }

    public void setListaZadan(ArrayList<Zadanie> listaZadan) {
        this.listaZadan = listaZadan;
    }
}
