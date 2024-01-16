package Firma;

import Firma.Zadanie.StatusZadania;
import Firma.Zadanie.TrybZadania;

import java.util.ArrayList;
import java.util.Random;

public class Main {
    public static void main(String[] args) {
        // Creating an ArrayList to store instances of Pracownik
        Random random = new Random();
        ArrayList<APracownik> pracownicy = new ArrayList<>();

        // Initializing 20 instances of Pracownik with random data and adding them to the ArrayList
        for (int i = 0; i < 10; i++) {
            pracownicy.add(new PracownikZwykly(generateRandomName(), generateRandomSurname(),
                    generateRandomPesel(), generateRandomSalary()));
            pracownicy.add(new PracownikSpecjalista(generateRandomName(), generateRandomSurname(),
                    generateRandomPesel(), generateRandomSalary(),(e) -> e*2));
        }


        ArrayList<Zadanie> zadania = new ArrayList<>();

        // Initializing 20 instances of Zadanie with random data and adding them to the list
        for (int i = 1; i <= 20; i++) {
            zadania.add(createRandomZadanie(i,pracownicy.get(random.nextInt(pracownicy.size()))));
        }

        ListaZasobow podOddzial1 = new ListaZasobow(pracownicy,zadania);

        System.out.println("DRUKUJEMY CALA FIRME:\n\n\n"+podOddzial1);
        System.out.println("DRUKUJEMY ODFILTROWANE ZADANIA O ETYKIECIE ZADANIE 5:\n\n\n"+podOddzial1.filtrujListeZadanIPosortujPilnoscia("Zadanie 5",null,null));
        System.out.println("\n\n\nDRUKUJEMY ODFILTROWANE ZADANIA O STATUSIE W_TOKU, BEDA ONE POSORTOWANE TRYBEM PILNOSCI:\n\n\n"+podOddzial1.filtrujListeZadanIPosortujPilnoscia(null,StatusZadania.W_TOKU,null));


    }

    // Helper method to create a Zadanie with random data
    private static Zadanie createRandomZadanie(int index,APracownik pracownik) {
        Random random = new Random();

        // Randomly selecting StatusZadania
        StatusZadania randomStatus = StatusZadania.values()[random.nextInt(StatusZadania.values().length)];

        // Randomly selecting TrybZadania
        TrybZadania randomTryb = TrybZadania.values()[random.nextInt(TrybZadania.values().length)];

        return new Zadanie("Zadanie "+index, randomStatus, randomTryb, pracownik);
    }

    // Getters and setters (you may generate them using your IDE or write them manually)

    // Helper methods for generating random data (similar to the previous example)

    private static String generateRandomName() {
        String[] names = {"Maciek", "Anna", "Jan", "Katarzyna", "Piotr", "Marta", "Tomasz", "Ewa"};
        Random random = new Random();
        return names[random.nextInt(names.length)];
    }

    private static String generateRandomSurname() {
        String[] surnames = {"Kowal", "Nowak", "Mazurek", "Lis", "Wójcik", "Zając", "Piotrowski", "Szymański"};
        Random random = new Random();
        return surnames[random.nextInt(surnames.length)];
    }

    private static String generateRandomPesel() {
        Random random = new Random();
        return String.format("%011d", random.nextInt(1000000000));
    }

    private static int generateRandomSalary() {
        Random random = new Random();
        return 3000 + random.nextInt(5000);
    }
}

