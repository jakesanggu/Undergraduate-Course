public class Book extends Material {
	
	static int total_books=1; //총 책의 개수를 저장한다. 이 정보가 고유의 아이디로 사용된다.
	
	public Book(String ti){
		super(ti); //super으로 Material의 생성자를 호출한다.
		state = AVAILABLE;//책을 생성시 열람/대여가가능한상태로 변경
		ID="B"+ total_books++; //책 고유의 아이디로 책(B)로 시작하며 뒤에는 등록된 순서의 번호이다.
	}
	public Book(String ti, String author){
		super(ti,author);//super으로 Material의 생성자를 호출한다.
		state = AVAILABLE; //책을 생성시 열람/대여가가능한상태로 변경
		ID="B"+ total_books++;  //책 고유의 아이디로 책(B)로 시작하며 뒤에는 등록된 순서의 번호이다.
	}
	public Book(){
		super();//super으로 Material의 생성자를 호출한다.
		state =UNCLASSIFIED; //만일 책의 이름이 정해지지 않으면, 대출/열람불가상태가 된다. 
	}

	@Override
	public void isBorrowed() {
		if(state ==AVAILABLE)
		state = BORROWED; //만일 책이 대여/열람이 가능한 상태면 이를 대여상태로 변환
	}

	@Override
	public void isReturned() {
		if(state != AVAILABLE) //반납의 경우 Borrowed 혹은 Reading이므로 둘중에 아니라면
		state = AVAILABLE;
	}
	@Override
	public void isRead(){
		if(state == AVAILABLE)
		state = READING; //책을 읽기 위해서는 available 상태이어야한다. 이를 READING 상태로 변경
	}
	
}
