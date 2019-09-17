
public class NonMember extends Visitor {

	public NonMember(String na, int ag) {
		super(na, ag);
		borrowLimit=3;//비회원은 최대 대출가능수가 3개이다. 생성자 초기화시 자동으로 상위 필드 borrowLimit에 값이 대입된다.
		
	}

	@Override
	public boolean isMember() {
		return false; //비회원은 false를 반환한다.
	}

}
