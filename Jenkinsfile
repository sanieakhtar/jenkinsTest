pipeline {
    agent any
    stages {
    	stage('clean') {
    		steps {
    			sh 'echo "cleaning project files..."'
    			sh 'make -C ./sw20200507/CPU1_FLASH/ -k -j 4 clean -O -s'
    			sh 'echo "project cleaned"'
    		}
    	}
    	
        stage('build') {
            steps {
            	sh 'echo "building python project.."'
                sh 'python3 --version'
                sh 'python3 *.py'
                sh 'echo " "'
                sh 'echo "building CCS project..."'
                sh 'make -C ./sw20200507/CPU1_FLASH/ -k -j 4 all -O -s'
                sh 'echo "finished building projects!"'
            }
        }
    }
}
