pipeline {
    agent any
    stages {
        stage('build') {
            steps {
                echo "Running ${env.BUILD_ID} on ${env.JENKINS_URL}"
                sh 'python3 --version'
                sh 'python3 somePython.py'
            }
        }
    }
}
