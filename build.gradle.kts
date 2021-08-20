plugins {
    `java-library`
    idea
    id("org.openjfx.javafxplugin") version "0.0.10"
}

repositories {
    mavenCentral()
}

dependencies {
    api("org.junit.jupiter:junit-jupiter:5.7.2")
    implementation("org.junit.jupiter:junit-jupiter:5.7.2")
    implementation("org.openjfx.javafxplugin:javafxplugin:0.0.10")
    testImplementation("org.junit.jupiter:junit-jupiter:5.7.2")
}

configurations {
    implementation {
        resolutionStrategy.failOnVersionConflict()
    }
}

sourceSets {
    main {
        java.srcDir("src/main/java")
    }
}

java {
    sourceCompatibility = JavaVersion.VERSION_11
    targetCompatibility = JavaVersion.VERSION_11
}

tasks {
    test {
        testLogging.showExceptions = true
    }
}