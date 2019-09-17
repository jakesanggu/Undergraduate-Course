
public abstract class Material {
	String title;  
	String author;
	String ID; //고유 인식번호 책이면 b1 ~ b .... 신문이면, n1  ~ n...
	int state; 	
	
	public static int AVAILABLE = 0;
	public static int READING = 1;
	public static int BORROWED = 2;
	public static int READ_ONLY = 3;	
	public static int BORROW_ONLY = 4;
	public static int UNCLASSIFIED =5;//확인할 수 없는 객체일때 

	public Material(){
		title = "Unkown";
		author= "Unkown";//생성자내의 인자가 전달되지 않으면, 확인할 수 없는 객체이다. 이
	}
	public Material(String ti){
		title = ti; //ti를 객체 title에 저장
		author = "Unkown";
	}
	public Material(String ti,String au){
		title = ti;
		author= au;
	}

	public abstract void isReturned(); // 반납 후 상태 변화 함수
	public abstract void isBorrowed(); // 대여 후 상태 변화함수
	public abstract void isRead(); // 읽기 후 상태변화
	


}
