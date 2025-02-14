# Apache Hadoop Manager - Lightweight Command-Line Tool for Hadoop Clusters

## 🚀 Introduction

Apache Hadoop Manager is a powerful command-line utility designed to simplify Hadoop cluster management with terminal efficiency. Unlike web-based solutions like Apache Ambari, this lightweight tool enables administrators and developers to monitor, configure, and maintain Hadoop ecosystems directly from the command line. Optimized for performance and automation, it reduces operational overhead while improving cluster management workflows.

---

## 🔑 Key Features

- **Command-Line Hadoop Cluster Management**  
  Control HDFS, YARN, HBase, Spark, Kafka, and 10+ services
- **Real-Time System Health Monitoring**  
  Check service statuses and cluster metrics instantly
- **Automated Configuration Deployment**  
  Streamline component updates and cluster scaling
- **Cross-Platform Support**  
  Works natively on Linux and Windows (via MinGW/MSYS2)
- **Task Automation**  
  Script routine operations with CLI-friendly output

---

## ⚙️ Prerequisites

| Platform | Requirements |
|----------|--------------|
| **Linux** | `gcc`, `make` (install via package manager) |
| **Windows** | [MSYS2](https://www.msys2.org/) or MinGW environment |

---

## 📥 Installation Guide

### 1. Clone Repository
git clone https://github.com/Debo-et/apache.git
cd apache/apache
## Installation Steps

### Linux
1. Compile the project using `make`:
   make
2. Install the compiled binaries:
   sudo make install
3. Add the installation path to the environment variable if it is not already:
   echo 'export PATH=/usr/local/bin:$PATH' >> ~/.bashrc
   source ~/.bashrc

### Windows (MSYS2 or MinGW)
1. Open an MSYS2 or MinGW terminal.
2. Navigate to the project directory:
   cd /c/path/to/apache
3. Compile the project:
   make
4. Install the compiled binaries:
   make install
5. manually add the path to the Windows Environment Variables)*


General Usage: The option is specified after the keyword 'apache'. 

apache [OPTION]...

Target Options:

--all               Check the status of all Hadoop ecosystem components.

--hdfs                  Provide a summary of the cluster's HDFS status.

--yarn                  List all NodeManagers and their statuses.

--hbase                 Show the cluster status of HBase.

--spark                 Check whether Spark is running.

--kafka                 Retrieve all available metrics for all topics within a Kafka broker.

--zookeeper             Check the cluster status of Zookeeper.

--flink                 Obtain Flink metrics.

--storm                 List running topologies.

--metastore             Check Hive Metastore reachability.

--hue                   Examine Hue status.

--pig                   Check if the Pig Grunt interactive shell is operational.

--oozie                 Check Oozie server status.

--presto                Check Presto cluster statistics.

--tez                   List running Tez applications.

--atlas                 Check Atlas status.

--ranger                Check Ranger status.

🧹 Maintenance
To remove compiled binaries and clean the project:
make clean

Using the Prebuilt Executable

If you have built the project using make, you can directly use the apache executable found in the project directory without needing to install it.

Support and Donations

If you find apache  command-line tool useful and would like to support its development, consider making a donation via PayPal:
Donate via PayPal yegetesurafel@yahoo.com

Your support helps keep this project maintained and improved. Thank you!

🤝 Contributing & Support

Found a bug? Open an issue
Want to contribute? Submit a pull request
Need help? Contact yegetesurafel@yahoo.com
