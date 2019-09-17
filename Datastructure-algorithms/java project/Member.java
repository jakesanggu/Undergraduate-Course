
public class Member extends Visitor {
	
	String ID;//방문객의 고유번호
	public Member(String na, int ag){
		super(na, ag);
		borrowLimit=5;//맴버의경우 5개의 제한이있다
		ID="M"+count++; //방문객의 고유번호는 "M"멤버 + 현재 인원 conut를 생성시 추가해준다. 즉 생성자가 호출되면 count를 증가시킨다.
		
	}

	public boolean isMember(){
		//도서관 멤버인지 확인하는 메소드로 멤버가 맞으면 true 아니면 false를 반환한다.
		
		return true;
	}
}
