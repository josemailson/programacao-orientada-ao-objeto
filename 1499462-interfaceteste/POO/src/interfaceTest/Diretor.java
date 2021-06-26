package interfaceTest;

public class Diretor extends Funcionario implements Autenticavel,Demitidor{

	@Override
	public void autentica() {
		System.out.println("diretor autenticando...");
		
	}

	@Override
	public void demite(Funcionario f) {
		System.out.println("demitindo "+f.getNome());
		
	}

	
}
