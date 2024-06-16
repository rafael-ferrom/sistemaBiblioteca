Biblioteca em C: Sistema de Empréstimo e Reserva de Livros Este projeto é um sistema de gerenciamento de empréstimo e reserva de livros desenvolvido em C. Ele permite o cadastro de alunos e livros, bem como a gestão de empréstimos e reservas.

Funcionalidades

Cadastro de Alunos: Permite cadastrar alunos, incluindo nome e RA. Cadastro de Livros: Permite cadastrar livros, incluindo título e autor. Exibição de Alunos: Mostra todos os alunos cadastrados ou um aluno específico. Exibição de Livros: Mostra todos os livros cadastrados, livros por status ou por título. Empréstimo de Livros: Gerencia o empréstimo de livros aos alunos. Devolução de Livros: Gerencia a devolução de livros emprestados. Reserva de Livros: Permite a reserva de livros pelos alunos. Deleção de Livros: Permite a remoção de registros de livros.

Estrutura do Código

Estruturas:

info_livro: Armazena informações sobre o status de um livro (Livre, Emprestado, Reservado) e seu registro. aluno: Contém informações do aluno, incluindo RA, nome, quantidade de livros emprestados e reservados, e uma tabela de livros associados. info_aluno: Armazena informações sobre o status de um aluno com relação a um livro específico. livro: Contém informações do livro, incluindo título, autor, registro, e status de empréstimo e reserva.

Funções

Funções de Alocação:

void aloca_aluno(aluno **palu, int qalu): Aloca memória para o número especificado de alunos. void aloca_livro(livro **pliv, int qliv): Aloca memória para o número especificado de livros.

Funções de Verificação:

int verifica_aluno(): Verifica a quantidade de alunos cadastrados no arquivo aluno.bin. int verifica_livro(): Verifica a quantidade de livros cadastrados no arquivo livro.bin.

Funções de Cadastro

void cadastro_aluno(aluno *palu): Realiza o cadastro de um novo aluno. void cadastro_livro(livro *pliv): Realiza o cadastro de um novo livro.

Funções de Gravação

void grava_aluno(aluno *palu): Grava os dados de um aluno no arquivo aluno.bin. void grava_livro(livro *pliv): Grava os dados de um livro no arquivo livro.bin.

Funções de Atualização

void atualiza_aluno(aluno *palu, int pos): Atualiza os dados de um aluno no arquivo aluno.bin. void atualiza_livro(livro *pliv, int pos): Atualiza os dados de um livro no arquivo livro.bin.

Funções de Busca

int busca_RA(aluno *palu, char *aux): Busca um aluno pelo RA. int busca_livro(livro *pliv, char *aux): Busca um livro pelo título. int busca_livro_reserva(livro *pliv, char *aux): Busca um livro reservado pelo título. int busca_livro_deleta(livro *pliv, int reg): Busca um livro pelo registro para deletar. int busca_livro_vago(livro *pliv, char *aux): Busca um livro vago pelo título. int devolve_livro(livro *pliv, char *aux): Busca um livro emprestado pelo título para devolução.

Funções de Exibição

void mostra_aluno_total(aluno *palu): Mostra todos os alunos cadastrados. void mostra_aluno_parcial(aluno *palu): Mostra os detalhes de um aluno específico. void mostra_livro_total(livro *pliv): Mostra todos os livros cadastrados. void mostra_livro_status(livro *pliv): Mostra livros por status. void mostra_livro_titulo(livro *pliv): Mostra detalhes de um livro específico pelo título.

Funções de Empréstimo e Devolução

void emprestimo(aluno *palu, livro *pliv): Realiza o empréstimo de um livro. void devolucao(aluno *palu, livro *pliv): Realiza a devolução de um livro.

Outras Funções

void deleta_livro(aluno *palu, livro *pliv): Deleta o registro de um livro. void troca_reserva(aluno *palu, int reg_livro): Troca a reserva de um livro por um empréstimo. void maiuscula(char *aux, int tam): Converte uma string para maiúsculas.

Requisitos

Compilador C (por exemplo, GCC) Sistema operacional compatível com a linguagem C (Windows, Linux, macOS)

Considerações Finais Este sistema é uma solução básica para o gerenciamento de empréstimos e reservas de livros. Pode ser expandido e melhorado com funcionalidades adicionais, como a integração com um banco de dados ou a criação de uma interface gráfica.****
