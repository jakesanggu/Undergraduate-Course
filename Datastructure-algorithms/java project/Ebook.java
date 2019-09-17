
public class Ebook extends Material {

	static int total_ebooks=1;
	/*Ebook Material 은 자료를 다운 받기 때문에 다음이 가능하다.
	 * 
	 * 1. 동시에 자료를 열람할 수 있다. 
	 * 2. 대여라는 과정이 필요없다.
	 * 3. 단 다른 자료와 비슷하게 개수 제한이 존재한다.
	*/
	
	public Ebook(String ti , String author)
	{
		super(ti,author);
		state = AVAILABLE; //ebook은 책과동일하다. 열람가능이다. 이 상태는 항상 열람가능이다.
		ID="E"+ total_ebooks++; //ebook의 고유 id를 마찬가지로 저장한다.
	}
	public Ebook(String ti)
	{
		super(ti);
		state = AVAILABLE;
		ID="E"+ total_ebooks++;
	}
	public Ebook() {
		super();
		state = UNCLASSIFIED;
	}
	
	
	@Override
	public void isReturned() {
	//ebook의 경우 state의 영향을 받지 않는다.
		
	}

	@Override
	public void isBorrowed() {
		//ebook의 경우 state의 영향을 받지 않는다.
	}

	@Override
	public void isRead() {
		//ebook의 경우 state의 영향을 받지 않는다.
		
	}

}
