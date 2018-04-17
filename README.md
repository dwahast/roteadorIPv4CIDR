programa em C usando POSIX Threads para simular um roteador IPv4 CIDR (_Classless Inter-Domain Routing_) [1] com um _firewall_. 

O problema de encaminhamento de pacotes no IPv4 CIDR é um caso típico de busca pelo prefixo máximo. Uma tabela de roteamento contém endereços de rede IP,  um tamanho de máscara em bits e o enlace para onde o pacote deve ser encaminhado.
