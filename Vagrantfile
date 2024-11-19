Vagrant.configure("2") do |config|

    config.vm.box = "ubuntu/bionic64"

    config.vm.network "private_network", type: "dhcp"

    config.vm.synced_folder "./", "/vagrant"
  
    config.vm.provision "shell", inline: <<-SHELL
      apt-get update
      apt-get install -y nasm gcc php make
  
      nasm --version
      gcc --version
      php --version
      make --version
  
      echo "Entorno de desarrollo configurado con nasm, gcc, php y make instalados."
    SHELL
  end
  