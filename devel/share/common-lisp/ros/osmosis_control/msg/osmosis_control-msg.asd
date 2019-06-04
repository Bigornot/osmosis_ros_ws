
(cl:in-package :asdf)

(defsystem "osmosis_control-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :geometry_msgs-msg
)
  :components ((:file "_package")
    (:file "TeleopMsg" :depends-on ("_package_TeleopMsg"))
    (:file "_package_TeleopMsg" :depends-on ("_package"))
  ))