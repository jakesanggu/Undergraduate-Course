public class LibraryManager {
	public static void main(String[] args) { 
		//Library 생성 
		Library lib = new Library();
	
		
		//Visitor 생성
		Visitor v1 = new Member("이상구", 25);
		Visitor v2 = new Member("심승보", 25);
		Visitor v3 = new NonMember("조재훈",24);
		Visitor v4 = new NonMember("김재민",23);
		
		lib.blcokmember.add(v2);
		lib.blcokmember.add(v3);
		
		//Material 생성 BOOKS	
		lib.materials.add(new Book("Digital Design"));
		lib.materials.add(new Book("Digital Design"));
		lib.materials.add(new Book("Digital Desig"
				+ "n"));
		lib.materials.add(new Book("Digital Design"));
		lib.materials.add(new Book("Digital Design"));
		lib.materials.add(new Book("Digital Design"));
		lib.materials.add(new Book("Digital Design"));
		lib.materials.add(new Book("Digital Design"));
		
		lib.materials.add(new Book("Electronic Circuit 1","Lee Sang Gu"));
		lib.materials.add(new Book("Electronic Circuit 2","Lee Sang Gu"));
		lib.materials.add(new Book("Circuit Analysis 1","David Chang"));
		lib.materials.add(new Book("Circuit Analysis 2","David Chang"));
		lib.materials.add(new Book("Electromagnetics 1","Sommers Erika"));
		lib.materials.add(new Book("Electormagnetics 2","Kuku Fenis"));
		lib.materials.add(new Book("Datastructures and Algorithm","Peter Cho"));
		lib.materials.add(new Book("Modern Physics","Saint Choise"));
		lib.materials.add(new Book("Fundamental Physics","Eienstien"));
		lib.materials.add(new Book("Matlab Basics","Peter Jackson"));
		lib.materials.add(new Book("The Incredible Hulk","Stan Lee"));
		
		
		lib.materials.add(new Ebook("E-Digital Design"));
		lib.materials.add(new Ebook("E-Digital Design"));
		lib.materials.add(new Ebook("E-The Incredible Hulk","Stan Lee"));
		
		//Material 생성 CD

		lib.materials.add(new CD("The Sound of Music"));
		lib.materials.add(new CD("The Sound of Music"));
		lib.materials.add(new CD("Begin Again"));
		lib.materials.add(new CD("Mario"));
		lib.materials.add(new CD("Starcraft 1"));
		
		//Material 생성 Newspaper
		lib.materials.add(new NewsPaper("Chosun 2018.6.5"));
		lib.materials.add(new NewsPaper("Chosun 2018.6.4"));
		lib.materials.add(new NewsPaper("Chosun 2018.6.3"));
		lib.materials.add(new NewsPaper("Chosun 2018.6.2"));
		lib.materials.add(new NewsPaper("Chosun 2018.6.1"));
		lib.materials.add(new NewsPaper("Chosun 2018.5.31"));
		lib.materials.add(new NewsPaper("Chosun 2018.5.30"));
		lib.materials.add(new NewsPaper("Chosun 2018.5.29"));
		lib.materials.add(new NewsPaper("Chosun 2018.5.28"));
		lib.materials.add(new NewsPaper("Chosun 2018.5.27"));
		lib.materials.add(new NewsPaper("DongA 2018.5.27"));
		lib.materials.add(new NewsPaper("DongA 2018.5.26"));
		lib.materials.add(new NewsPaper("DongA 2018.5.25"));
		lib.materials.add(new NewsPaper("DongA 2018.5.24"));
		lib.materials.add(new NewsPaper("DongA 2018.5.23"));
		lib.materials.add(new NewsPaper("DongA 2018.5.22"));
		lib.materials.add(new NewsPaper("DongA 2018.5.21"));
		lib.materials.add(new NewsPaper("DongA 2018.5.20"));
		lib.materials.add(new NewsPaper("DongA 2018.5.19"));
		lib.materials.add(new NewsPaper("DongA 2018.5.18"));
				
		//시나리오 진행
		lib.enter(v1);
		lib.enter(v2);
		lib.enter(v3);
		lib.enter(v4);
		lib.borrowMaterial(v1,"The Sound of Music");
		lib.borrowMaterial(v1,"Begin Again");
		lib.readMaterial(v1, "DongA 2018.5.18");
		lib.readMaterial(v1, "Mario");
		lib.readMaterial(v1, "Matlab Basics");
		
		lib.readMaterial(v4, "Mario");
		lib.readMaterial(v4, "DongA 2018.5.20");
		lib.borrowMaterial(v4,"E-The Incredible Hulk");
		lib.showLibraryStatus();
		lib.exit(v1);
		lib.exit(v4);
		lib.returnMaterial(v1, "DongA 2018.5.18");
		lib.exit(v1);
		lib.returnMaterial(v1, "Matlab Basics");
		lib.returnMaterial(v1, "Mario");
		lib.returnMaterial(v4, "DongA 2018.5.20");
		lib.exit(v4);
		lib.exit(v1);

	}
}
