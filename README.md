## [de]coder

Este é um projeto realizado como TP para a p2 do 1º semestre de engenharia da computação da Unisanta. Sua função é codificar e decodificar frases, palavras, arquivos de texto, entre outros. O projeto se utiliza de um sistema simples de geração de chaves randômicas de criptografia que ficam armazenadas nas próprias strings geradas que se comporta dentro dos conformes da tabela ASCII. Seu código fonte foi inteiramente escrito em C, com alguns elementos de C++, pois o projeto pede para que ela seja compilada em C++.

-------------------
### Como usar

##### O projeto é constituído pelas seguintes funções básicas:

- Login, o usuário deve criar uma senha ao abrir o programa pela primeira vez, e utilizá-la para acessá-lo novamente.
- Log de usuário, para todo evento, é criado um log no arquivo user_log, contendo a data atual e informações sobre o evento formatadas amigavelmente.

- Codificar, com a opção de codificar um texto entrado pelo usuário, ou o texto contido no arquivo gerado pela decodificação, armazena resultados em txt_codificado.
- Decodificar, com as mesmas opções de codificar, porém fazendo o processo inverso, armazena resultados em txt_decodificado.
- Teste, função requisito do projeto que codifica e decodifica uma mensagem padrão.
- Modificar senha, troca a senha definida pelo usuário.
- Sair, fecha o programa.
------------------------------------

### Como instalar/compilar o projeto:

Você pode:

1 - Baixar o programa na aba release desse projeto e abrir o arquivo .exe contido no arquivo compresso.
2 - Baixar/clonar o repositório e compilar e/ou modificar o código-fonte como desejar no seu IDE/compilador favorito.

----------------------------------
### Changelog

1. v1.0
	- Primeiro release.
