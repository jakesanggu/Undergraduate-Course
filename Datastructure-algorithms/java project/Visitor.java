import java.util.ArrayList;

public abstract class Visitor {
	String name; 
	int age;	
	int borrowLimit;
	static int count=1;//방문객의 총 수 이다.
	
	ArrayList<Material> hands = new ArrayList<Material>(); // 소유물 변수로 arrayList를 통하여 구현하였다
	
	public Visitor(String na, int ag){
		name=na; age=ag;
	}
	
	public abstract boolean isMember();//맴버인지 확인하는 추상 메소드
}
