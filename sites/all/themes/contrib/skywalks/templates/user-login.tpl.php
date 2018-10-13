<?php drupal_add_css(drupal_get_path('theme', 'skywalks') . '/css/login.css'); ?>
<div class="yourtheme-user-login-form-wrapper">
	<?php hide($form['name']); ?>
	<?php hide($form['pass']); ?>
	<?php hide($form['actions']); ?>
	<?php print drupal_render_children($form) ?>
</div>
<div class="container-scroller">
	<div class="container-fluid page-body-wrapper full-page-wrapper auth-page">
		<div class="content-wrapper d-flex align-items-center auth auth-bg-1 theme-one">
			<div class="row w-100">
				<div class="col-lg-4 mx-auto">
					<div class="auto-form-wrapper">	
					<h2 class="text-center"><?php print render($intro_text); ?></h2>
						<form action="/user" method="post" id="user-login" accept-charset="UTF-8">
							<div class="form-group">
								<label class="label">Username</label>
								<div class="input-group">
									<?php print render($form['name']); ?>
									<div class="input-group-append">
										<span class="input-group-text">
											<i class="mdi mdi-check-circle-outline"></i>
										</span>
									</div>
								</div>
							</div>
							<div class="form-group">
								<label class="label">Password</label>
								<div class="input-group">
									<?php print render($form['pass']); ?>
									<div class="input-group-append">
										<span class="input-group-text">
											<i class="mdi mdi-check-circle-outline"></i>
										</span>
									</div>
								</div>
							</div>
							<div class="form-group">
								<button class="btn btn-primary submit-btn btn-block">Login</button>
							</div>
							<div class="form-group d-flex justify-content-between">
								<a href="user/password" class="text-small forgot-password text-black">Forgot Password</a>
							</div>
								<div class="text-block text-center my-3">
									<span class="text-small font-weight-semibold">Not a member ?</span>
									<a href="user/register" class="text-black text-small">Create new account</a>
								</div>
							</form>
						</div>
						<ul class="auth-footer">
							<li>
								<a href="#">Conditions</a>
							</li>
							<li>
								<a href="#">Help</a>
							</li>
							<li>
								<a href="#">Terms</a>
							</li>
						</ul>
						<p class="footer-text text-center">copyright © 2018 Skywalks. All rights reserved.</p>
					</div>
				</div>
			</div>
			<!-- content-wrapper ends -->
		</div>
		<!-- page-body-wrapper ends -->
	</div>

