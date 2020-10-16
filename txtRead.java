
import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;

public class txtRead {  
    public static void main(String[] args) {
        try{
            File file = new File("/ras_test/led_test_data.txt");
            FileReader filereader = new FileReader(file);
            BufferedReader butReader = new BufferedReader(filereader);


            ArrayList<String> linelist = new ArrayList<String>();
            String linestr = "";
            while((linestr = butReader.readLine()) != null) {
//                System.out.println(linestr); // txt파일 저장
                linelist.add(linestr); // 저장된 값 배열로 저장
            }
            System.out.println(linelist.get(0)); // 배열에서 원하는 인덱스 값 출력

            butReader.close();
        } catch(FileNotFoundException e) {
            System.out.println("Have No FileList@@");
        } catch(IOException e) {
            System.out.println(e);
        }
    }
}
