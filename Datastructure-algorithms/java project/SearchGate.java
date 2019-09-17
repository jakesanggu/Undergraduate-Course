public class SearchGate {
	
	public boolean search(Visitor v){
	for(Material im : v.hands) //방문객이 대여하지 않은 자료를 가지고 나갈떄 탐지
	{
		if(im.state != Material.BORROWED && !(im instanceof Ebook)) //만약 STATE가 BORROWED가 아니라면, 오로지 BORROWED된 자료만 들고 나갈 수 있다.
		{ //EBOOK은 그냥 가지고 나갈 수 있다.
			System.out.println("[삐삐삐] 나갈수 없음! " + v.name + "님 아직 대여하지 않는 책 "+im.title +" 이 존재합니다.");
			return false;//나가는것을 불허한다.
		}
	}
		
		return true;//나가는거 허락
	}
	
	
	public boolean enter(Visitor v) //도서관에 입장시 차단회원인지 판별
	{
		if(Library.blcokmember.contains(v)) {//차단회원 리스트에 방문객의 객체가 있다면
			System.out.println("[삐삐삐]"+v.name+"님 미납하신 연체 요금을 먼저 사무소에서 납부해주세요");
			return false;//입장거부
		}
		
		else
		return true;
	}
	
}
