
public class CD extends Material {	
	static int total_cd=1; //cd 의 개수를 저장한다. 이 정보가 고유의 아이디로 사용된다.
	public CD() {
		super();//super으로 Material의 생성자를 호출한다.
		state =UNCLASSIFIED; //만일 CD의 이름이 정해지지 않으면, 대출/열람불가상태가 된다. 
	}
	public CD(String title, String author) {
		super(title,author);//super으로 Material의 생성자를 호출한다.
		state = BORROW_ONLY; //cd를 생성시 시디는 대여가능상태로 바뀐다.
		ID="C"+ total_cd++;
	}
	public CD(String title) {
		super(title);//super으로 Material의 생성자를 호출한다.
		state = BORROW_ONLY;
		ID="C"+ total_cd++;// 시디의 c + 고유의 키값이 id이다.
	}
	
	@Override
	public void isBorrowed() {
		if(state ==BORROW_ONLY) //cd 가 대여가능 상태이면, cd는 대여만 가능하므로
		state = BORROWED;//대여한다.
	}

	@Override
	public void isReturned() {
		if(state != BORROW_ONLY)
		state = BORROW_ONLY;
	}
	@Override
	public void isRead(){
		
	}
	

}
