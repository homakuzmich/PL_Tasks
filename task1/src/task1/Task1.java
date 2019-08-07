package task1;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class Task1 {

    public static void writeInFile(int k1, int k2) throws IOException {

        try (FileWriter nFile = new FileWriter("file.txt")) {
            for (int i = k1; i < k2; i++) {

                int n = (int) (Math.random() * (65536 + 1)) - 32768;
                final String s = Integer.toString(n);
                nFile.write(s + "\n");
            }
        }
    }

    public static void getList() throws FileNotFoundException {
        List<Double> list = new ArrayList<>();
        File file = new File("file.txt");
        BufferedReader reader = null;

        try {
            reader = new BufferedReader(new FileReader(file));
            String text = null;

            while ((text = reader.readLine()) != null) {
                list.add(Double.parseDouble(text));
            }
        } catch (FileNotFoundException e) {
            e.getMessage();
        } catch (IOException e) {
            e.getMessage();
        } finally {
            try {
                if (reader != null) {
                    reader.close();
                }
            } catch (IOException e) {

            }
        }

        //вычисление 90-го перцентиля
        Collections.sort(list);
        System.out.printf("%.2f %n", list.get(list.size() * 9 / 10));

        //вычисление максимума
        double maximum = Double.MIN_VALUE;
        Double[] item = list.toArray(new Double[list.size()]);
        for (Double item1 : item) {
            maximum = Math.max(maximum, item1);
        }
        System.out.printf("%.2f %n", maximum);

        //вычисление минимума
        double minimum = Double.MAX_VALUE;
        for (Double item1 : item) {
            minimum = Math.min(minimum, item1);
        }
        System.out.printf("%.2f %n", minimum);

        //вычисление медианы
        if (item.length % 2 == 0) {
            System.out.printf("%.2f %n", item[item.length / 2] + item[item.length / 2 - 1] / 2d);
        } else {
            System.out.printf("%.2f %n", item[item.length / 2]);
        }

        //вычисление среднего
        double arithmetic = 0;
        for (Double item1 : item) {
            arithmetic += item1;
        }
        System.out.printf("%.2f", arithmetic / item.length);

    }

    public static void main(String[] args) throws IOException {
        int k1 = 0;
        int k2 = 998;
        writeInFile(k1, k2);

        getList();

    }

}
