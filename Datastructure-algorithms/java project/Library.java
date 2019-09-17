import java.util.ArrayList;

public class Library {
	
	ArrayList<Material> materials = new ArrayList<Material>();// 소장 자료들을 저장하는 배열
	ArrayList<Visitor> visitors = new ArrayList<Visitor>();// 입장한 방문객들의 목록을 저장하는 배열
	ArrayList<Visitor> members = new ArrayList<Visitor>();// 회원 목록 배열
	static ArrayList<Visitor> blcokmember = new ArrayList<Visitor>(); //추가기능으로 차단멤버 회원 목록을 리스트에 담아놨다.
	
	SearchGate gate = new SearchGate(); //도서관에 출입하는 보안검색대
	
	public boolean enter(Visitor v){ //방문자가 방문을 하면
		if(gate.enter(v)) //보안검색대에 통과한 사람만 입장가능, 차단 회원은 입장 불가
		{	
		System.out.println(v.name+" 입장하였습니다.");
		visitors.add(v);//visitors 리스트에 해당 방문객 객체 추가
		if(v instanceof Member) {members.add(v);} //만약 방문자가 회원이라면 회원 목록에 추가
		System.out.println("현재 방문객 수: "+visitors.size());
		return true;
		}
		else
		return false; //차단회원이라면 입장을 안시킨다.
	}
	
	public void exit(Visitor v){
		if(gate.search(v)){  // 도서관 외부로 나갈떄 메소드 만약 대여하지 않는 자료가있다면 나가지 못함
			System.out.println(v.name+" 퇴장합니다");
			visitors.remove(v); //성공적으로 리스트에서 해당 객체 제거
			if(v instanceof Member) {members.remove(v);} //만약 회원이라면, 회원명단에서도 제거 
			System.out.println("현재 방문객 수: "+visitors.size());		
		}		
	}
	
public boolean borrowMaterial(Visitor v, String ti){ //방문자 V가 ti라는 자료를 원할때 
		//우선 동일한 material 이 몇개 있는지 찾아보고 대여가능한 material 의 개수를 추출한다.
		int avail=0, using = 0;
		//avail은 실질적으로 대여가 가능한 자료의 수  , using은 현재 대여가 불가능하며 다른사람이 읽거나 대여한 수
		if(v.hands.size() >= v.borrowLimit){ //만약 방문개의 손애 들고있는 material이 초과 개수이면 
			System.out.println(v.name+"는(은) 더이상 빌릴 수 없습니다.");
			return false; //일단 초과적으로 대여한사람은 거절한다.
		}
			
		for (Material im : materials){
		if(im.title.equals(ti))
		{ //방문객이 원하는 자료가 있는 지 탐색
			if(im instanceof NewsPaper) {	System.out.println("신문 자료는 빌릴 수 없어 " + v.name+" 의 대출 요청을 거절합니다"); return false;	}		
			if(im.state == Material.AVAILABLE || im.state == Material.BORROW_ONLY) {avail++;}
			else if(im.state == Material.BORROWED || im.state == Material.READING) {using++;}
			
			//여기서 avail즉 방문객이 원하는 자료가 가능한 수, using 방문객이 원하지만 현재 대여/읽는 자료의 수
		}	

		}
		
		if(avail >0)
		{//만약 자료가 1개이상이라면 대여 절차를 밟는다.
			for (Material im : materials)
			{//해당 자료를 다시 for each루프를 통하여 찾는다.
				if(im.title.equals(ti) && (im.state==Material.AVAILABLE || im.state ==Material.BORROW_ONLY) ){ //만약 merterial이 AVAILABLE이면 
					v.hands.add(im); //방문객의 소지품 배열에 넣는다.
					System.out.println(v.name+"에게 자료 \""+ti+"\" (ISBN: "+im.ID+") 을(를) 대출 합니다"+"[현재 대여/읽기 수:"+(v.hands.size())+"]");	//v에게 자료를 대여한다.			
					im.isBorrowed(); //그리고 그 자료를 Borrowed 로 한다.
					return true; }
					
			}	
		}
		else
		{ //만일 실제로 가능한 자료가 없다면 , using =0이라면 이 자료는 원래없는 자료다. 만일 using이 1보다 크면 현재 다른사람이 대여중인자료
			if(using ==0){	System.out.println("자료 \""+ti+"\" 가 없어 "+v.name+"의 대출 요청을 거절합니다"); return false; }
			else {	System.out.println("\""+ti+"\"자료가 대여[읽기]중 이므로" + v.name+" 의 대출 요청을 거절합니다"); 	return false; }
		}
	

return false;
}
	


public boolean readMaterial(Visitor v, String ti){
		for (Material im : materials){//for-each문을 이용하여 ti라는 자료를 찾는다.
			if(im.title.equals(ti)){//만약 ti라는 자료와 동일한 자료가 있으면
				if(im.state==Material.AVAILABLE || im.state==Material.READ_ONLY){
					v.hands.add(im); //방문객의 소지품에 추가
					System.out.println(v.name+" 이(가) 자료 \""+ti+"\" 을(를) 열람합니다");
					im.isRead();//자료를 열람상태로 변경
					return true;
				}
				else
				{
					System.out.println("자료 \""+ti+"\"를 열람할 수 없습니다");
					return false;
				}
			}			
		}
		System.out.println("자료 \""+ti+"\" 가 없어 "+v.name+"의 열람요청을 거절합니다");
		return false;
	}
	
public void returnMaterial(Visitor v, Material m){
		for(Material im : v.hands){//자료를 반환하는 메소드 반환메소드 탐색
			if (im.equals(m)){//만약 자료와 반환자료가 동일하면
				System.out.println(v.name+"이(가) \""+im.title + "\" (ISBN:" + im.ID + ")을(를) 반납합니다. 현재 대여/읽기: "+v.hands.size()+"(개)");
				v.hands.remove(im);//방문객의 소지품에서 제거
				im.isReturned();//자료를 available read_only로 수정
				return;
			}
		}
		System.out.println("[반납실패] "+m.title+" 반납할 도서가 존재하지 않습니다!");
		return;				
	}
	
public void returnMaterial(Visitor v, String ti) //위와 동일한 함수지만 , 인자가 다름 오버라이딩 되어있다. 
	{
		for(Material im : v.hands) //for each문을 탐색하여 사용자가 반환하고자하는 자료를 찾는다.
		{
			if (im.title.equals(ti))
			{
				v.hands.remove(im); //제거후
				System.out.println(v.name+"이(가) \""+im.title + "\" (ISBN:" + im.ID + ")을(를) 반납합니다. 현재 대여: "+v.hands.size()+"(개)");
				im.isReturned();//해당자료를 제거한다.
				return;
			}
		
		}
		
		System.out.println("[반납실패] "+ti+" 가 존재하지 않습니다!");
		return;				
	
	}

public void showLibraryStatus() //현재 도서관 상태를 체크한다.
{
	System.out.println("-------------------------------------------------------------------------------------");
	System.out.println("도서관 이용자: "+visitors.size()+" 명 입니다."+"회원: "+ members.size() +" 명 "+" 비회원 "+(visitors.size()-members.size())+" 명");
	//리스트를 확인하여, 현재 회원의 수와 비회원의 수를 나타낸다. visitor.size()메소드는 이를 출력해준다.
	for(Visitor vi: visitors)
	{
		//도서관내의 방문객 리스트 visitors에 접근하여 모든 사람의 소지품 (대여/읽기)를 확인하다.
		System.out.print(vi.name+" 현재 대여 정보: ");
		for(Material ma :vi.hands) 
		{
		System.out.print(ma.title+" |");
		}
		System.out.println("");
	}

	System.out.println("-------------------------------------------------------------------------------------");
}

	

}
