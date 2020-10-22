import java.io.DataInputStream;
import java.io.DataOutput;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;

public class SOCKET {
	
	 public static void main(String[] args) throws IOException {
		
		ServerSocket serversocket = null;
		
		try {
			serversocket = new ServerSocket(6112);
			System.out.println("서버 대기중");
		}catch(IOException e) {
			e.printStackTrace();
		}
		
		while (true) {
		String str = null;
			try {
				System.out.println("wait..............");
				Socket socket = serversocket.accept();
				
				byte[] bytes = null;
				InputStream is = socket.getInputStream();
				
				bytes = new byte[100];
				int readByteCount = is.read(bytes);
				
				str = new String(bytes, 0, readByteCount, "UTF-8");
				
				System.out.println(str);
			} catch (Exception e) {
				// TODO: handle exception
				e.printStackTrace();
			}
		}
	}
}