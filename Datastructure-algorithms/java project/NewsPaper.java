
public class NewsPaper extends Material {

	static int total_newspaper=1;
	
	public NewsPaper() {
		super();
		state = UNCLASSIFIED; //생성자 인자부족시 알수없는 자료로 구분
	}
	public NewsPaper(String title, String author) {
		super(title,author);
		state = READ_ONLY;
		ID="N"+ total_newspaper++; //모두 동일하게 N + 신문 고유키를 한다. 생성자 호출시 자동으로 클래스변수 TOTAL_NEWSPAPAER의 값이 증가
	}
	public NewsPaper(String title) {
		super(title);
		state = READ_ONLY;
		ID="N"+ total_newspaper++;
	}
	
	
	
	@Override
	public void isBorrowed() {
	//신문은 빌릴수가 없으므로 state를 바꾸지 않는다.
	}

	@Override
	public void isReturned() {
		if(state != READ_ONLY)
		state = READ_ONLY; //신문은 읽기만 가능하므로, 반환은 항상 Read_only로 바꾸어준다.
	}
	@Override
	public void isRead(){
		
		if(state == READ_ONLY) //신문은 Read_only -> Reading으로 두개의 상태만 가능하다.
		state = READING;
		
	}
	

}
